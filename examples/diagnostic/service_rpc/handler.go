package servicerpc

type MessageContext struct {
	ResponseData             []byte
	RequestData              []byte
	RequestType              uint8
	SuppressPositiveResponse uint8
	SourceOfRequest          uint8
	ContextID                uint8
	RxPduID                  int8
}

type Handler func(opStatus uint8, ctx *MessageContext, errorCode *uint8) uint8

func notImplemented(_ uint8, _ *MessageContext, errorCode *uint8) uint8 {
	*errorCode = 0
	return 0xDA // Example disabled/not-implemented result
}

var handlers = map[string]map[string]Handler{
	"MyService": {
		"Diagnostic":  notImplemented,
		"Reset":       notImplemented,
		"ReadMemory":  notImplemented,
		"WriteMemory": notImplemented,
	},
}

func dispatch(message ServiceRpcMessage) ServiceRpcMessage {
	call := decodeInvoke(message.Payload) // Decode the FlatBuffers union.
	ctx := call.MessageContext            // Byte vectors pass through unchanged.
	errorCode := uint8(0)
	result := uint8(0xDA)

	if service := handlers[call.ServiceName]; service != nil {
		if handler := service[call.FunctionName]; handler != nil {
			result = handler(call.OpStatus, &ctx, &errorCode)
		}
	}

	return ServiceRpcMessage{
		CallID: message.CallID,
		Payload: InvokeReturn{
			ReturnValue:    result,
			ErrorCode:      errorCode,
			MessageContext: ctx,
		},
	}
}
