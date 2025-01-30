// Copyright 2021 Robert Bosch GmbH
//
// SPDX-License-Identifier: Apache-2.0

#include <stdint.h>
#include <stdio.h>
#include <msgpack.h>
#include <automotive_bus_schema/signal/channel_builder.h>


#undef ns
#define ns(x) FLATBUFFERS_WRAP_NAMESPACE(AutomotiveBus_Signal_Channel, x)


int main(int argc, char **argv)
{
    /* Model UID and signals.*/
    uint32_t model_uid = 2911;
    uint32_t signal_count = 2;
    uint32_t signal_uid[2] = { 42, 24 };
    double signal_val[2] = { 42.0, 24.0 };

    /* Encode SignalWrite MsgPack payload: data:[ubyte] = [[UID],[Value]]. */
    msgpack_sbuffer sbuf;
    msgpack_packer pk;
    msgpack_sbuffer_init(&sbuf);
    msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);
    /* First(root) Object, array, 2 elements. */
    msgpack_pack_array(&pk, 2);
    /* 1st Object in root Array, list of UID's. */
    msgpack_pack_array(&pk, signal_count);
    for (uint32_t i = 0; i < signal_count; i++) {
        msgpack_pack_uint32(&pk, signal_uid[i]);
    }
    /* 2st Object in root Array, list of Values. */
    msgpack_pack_array(&pk, signal_count);
    for (uint32_t i = 0; i < signal_count; i++) {
        msgpack_pack_double(&pk, signal_val[i]);
    }

    /* Build the FBS Messages. */
    flatcc_builder_t builder, *B = &builder;
    flatcc_builder_init(B);
    /* Set the builder to prefix the buffer with the Message Size (needed for
       processing a stream of FBS Messages). */
    B->buffer_flags |= flatcc_builder_with_size;
    /* Create SignalWrite Message.*/
    flatbuffers_uint8_vec_ref_t data_vector;
    data_vector = flatbuffers_uint8_vec_create(B, (uint8_t*)sbuf.data, sbuf.size);
    ns(MessageType_union_ref_t) message;
    message = ns(MessageType_as_SignalWrite(
        ns(SignalWrite_create(B,
            data_vector,                // data
            0                           // immediate = false (default)
        ))
    ));
    /* Create the Channel Message, containing the SignalWrite Message. */
    ns(ChannelMessage_ref_t) channel_message;
    ns(ChannelMessage_start)(B);
    ns(ChannelMessage_model_uid_add)(B, model_uid);
    ns(ChannelMessage_message_add_value)(B, message);
    ns(ChannelMessage_message_add_type)(B, message.type);
    channel_message = ns(ChannelMessage_end)(B);

    /* Construct the FBS buffer, ready for transmission. */
    uint8_t *buf;
    size_t size;
    flatcc_builder_create_buffer(B,
        flatbuffers_identifier,
        B->block_align,
        channel_message,
        B->min_align,
        B->buffer_flags
    );
    buf = flatcc_builder_finalize_buffer(B, &size);
    printf("FBS Buffer:\n");
    printf("----------\n");
    for (size_t i = 0; i < size; i++) {
        printf("%02x ", buf[i]);
        if (i % 16 == 15) printf("\n");
    }

    /* Cleanup. */
    FLATCC_BUILDER_FREE(buf);
    flatcc_builder_clear(B);
    exit(0);
}
