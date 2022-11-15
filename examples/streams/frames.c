/* Copyright (C) 2022 Robert Bosch GmbH */

#include <stdio.h>
#include <stdint.h>
#include <automotive_bus_schema/stream/frame_builder.h>


#undef ns
#define ns(x)    FLATBUFFERS_WRAP_NAMESPACE(AutomotiveBus_Stream_Frame, x)
#define NODE_UID 49


typedef struct CanFrame {
    uint32_t frame_id;
    uint8_t  frame_type;

    uint32_t bus_id;
    uint32_t node_id;
    uint32_t interface_id;

    uint8_t *payload;
    uint8_t  length;
} CanFrame;


static void initialize_stream(flatcc_builder_t *B)
{
    flatcc_builder_reset(B);
    ns(Stream_start_as_root_with_size(B));
    ns(Stream_frames_start(B));
}


static void encode_CanFrame(flatcc_builder_t *B, struct CanFrame CanFrame)
{
    ns(Stream_frames_push_start(B));
    ns(CanFrame_start(B));
    ns(CanFrame_frame_id_add(B, CanFrame.frame_id));
    ns(CanFrame_payload_add(
        B, flatbuffers_uint8_vec_create(B, CanFrame.payload, CanFrame.length)));
    ns(CanFrame_frame_type_add(B, CanFrame.frame_type));
    ns(CanFrame_bus_id_add(B, CanFrame.bus_id));
    ns(CanFrame_node_id_add(B, CanFrame.node_id));
    ns(CanFrame_interface_id_add(B, CanFrame.interface_id));
    ns(Frame_f_CanFrame_add(B, ns(CanFrame_end(B))));
    ns(Stream_frames_push_end(B));
}


static void finalize_stream(
    flatcc_builder_t *B, uint8_t **buffer, size_t *length)
{
    ns(Stream_frames_end(B));
    ns(Stream_node_uid_add(B, NODE_UID));
    ns(Stream_end_as_root(B));
    *buffer = flatcc_builder_finalize_buffer(B, length);
}


static void process_CanFrame(ns(CanFrame_table_t) frame)
{
    flatbuffers_uint8_vec_t payload = ns(CanFrame_payload(frame));
    size_t                  length = flatbuffers_uint8_vec_len(payload);

    printf("CAN Frame:\n");
    printf("  frame_id     = %d\n", ns(CanFrame_frame_id(frame)));
    printf("  payload      = ");
    for (size_t _ = 0; _ < length; _++) printf("%02x ", payload[_]);
    printf("\n");
    printf("  length       = %ld\n", length);
    printf("  frame_type   = %d\n", ns(CanFrame_frame_type(frame)));
    printf("  bus_id       = %d\n", ns(CanFrame_bus_id(frame)));
    printf("  node_id      = %d\n", ns(CanFrame_node_id(frame)));
    printf("  interface_id = %d\n", ns(CanFrame_interface_id(frame)));
}


static void process_stream(uint8_t *buffer, size_t length)
{
    size_t   msg_len = 0;
    uint8_t *msg_ptr = buffer;

    if (buffer == NULL) return;

    /* Process the data stream. */
    printf("Process stream (length = %ld)\n", length);
    while (((msg_ptr - buffer) + msg_len) < (uint32_t)length) {
        /* Messages start with a size prefix. */
        msg_ptr = flatbuffers_read_size_prefix(msg_ptr, &msg_len);
        if (msg_len == 0) break;
        if (!flatbuffers_has_identifier(msg_ptr, flatbuffers_identifier)) break;

        /* Decode the frames. */
        ns(Stream_table_t) stream;
        stream = ns(Stream_as_root(msg_ptr));
        printf("Sending Node UID is: %u\n", ns(Stream_node_uid(stream)));
        ns(Frame_vec_t) vector = ns(Stream_frames(stream));
        size_t vector_len = ns(Frame_vec_len(vector));
        for (uint32_t _vi = 0; _vi < vector_len; _vi++) {
            ns(Frame_table_t) frame = ns(Frame_vec_at(vector, _vi));
            if (!ns(Frame_f_is_present(frame))) continue;
            ns(FrameTypes_union_type_t) frame_type = ns(Frame_f_type(frame));
            switch (frame_type) {
            case ns(FrameTypes_CanFrame):
                process_CanFrame(ns(Frame_f(frame)));
                break;
            default:
                printf("Not supported frame type\n");
                break;
            }
        }

        /* Next message in the stream. */
        msg_ptr += msg_len;
    }
}


int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    /* Setup the FBS Builder. */
    flatcc_builder_t builder, *B;
    B = &builder;
    flatcc_builder_init(B);
    B->buffer_flags |= flatcc_builder_with_size;

    /* Generate a stream of frames (in a single FBS message). */
    initialize_stream(B);
    encode_CanFrame(B, (struct CanFrame){
        .frame_id = 42,
        .bus_id = 1,
        .payload = (uint8_t *)"foo",
        .length = 3 });
    encode_CanFrame(B, (struct CanFrame){
        .frame_id = 24,
        .bus_id = 1,
        .payload = (uint8_t *)"bar",
        .length = 3 });
    uint8_t *buffer = NULL;
    size_t   length = 0;
    finalize_stream(B, &buffer, &length);

    /* Process the stream of frames. */
    process_stream(buffer, length);
    flatcc_builder_free(buffer);

    /* Clear out the FBS Builder. */
    flatcc_builder_clear(&builder);

    exit(0);
}
