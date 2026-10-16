// Copyright 2026 Robert Bosch GmbH
//
// SPDX-License-Identifier: Apache-2.0

package servicerpc

// MessageContext is a small example-only representation of the Service RPC
// message context. It intentionally keeps byte vectors as []byte so this file can
// compile without generated FlatBuffers bindings.
type MessageContext struct {
	ResponseData             []byte
	RequestData              []byte
	RequestType              uint8
	SuppressPositiveResponse uint8
	SourceOfRequest          uint8
	ContextID                uint8
	RxPduID                  int8
}

// InvokeCall is the decoded shape used by the example dispatcher.
type InvokeCall struct {
	ServiceName    string
	FunctionName   string
	OpStatus       uint8
	MessageContext MessageContext
}

// InvokeReturn is the example response payload.
type InvokeReturn struct {
	ReturnValue    uint8
	ErrorCode      uint8
	MessageContext MessageContext
}

// ServiceRpcMessage is an example-only envelope. A complete implementation would
// use the generated FlatBuffers accessors/builders for the Payload union.
type ServiceRpcMessage struct {
	CallID  uint32
	Payload any
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
	call := decodeInvoke(message.Payload) // Placeholder until union decoding is implemented.
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

func decodeInvoke(payload any) InvokeCall {
	switch call := payload.(type) {
	case InvokeCall:
		return call
	case *InvokeCall:
		if call != nil {
			return *call
		}
	}

	// The example is intentionally non-functional at this stage. Unknown payloads
	// dispatch to the default not-implemented response.
	return InvokeCall{}
}
