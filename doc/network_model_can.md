![Automotive Bus Schema](images/automotive-bus-schema_logo.png)


<!---
  Copyright (c) 2021 for information on the respective copyright owner
  see the NOTICE file and/or the repository https://github.com/boschglobal/automotive-bus-schema

  SPDX-License-Identifier: Apache-2.0
-->


## Network Model CAN

Model  | Network Model CAN  
:---|:---
&ensp; | [Schema File](../schemas/network_model_can.fbs)
MIME Type  | application/x-open-simulation-interface-network-model; type=CAN;
Data Stream | 4 byte Message Length followed by FlatBuffers Message. Repeating.  
FlatBuffers File Identifier | NMCA
Abbreviations  |  NM CAN, NMC, NMCA

### Modeled BUS Features


#### Tx/Rx FIFO(Buffer) Operation

The size and configuration of FIFO/Buffer is set when connecting to a Virtual BUS. Typically this is a limited resource and FIFO/Buffers are assigned to one of the Tx/Rx functions.


##### TX FIFO with Priority

* TX Queue with maximum size.
* Messages are sent according to Message ID.
  - has priority of TX FIFO in all cases (lower prio message here is still sent first)
* Bus arbitrates according to Message ID (Frame ID).
* Status message (on each BUS operation) includes:
  - list of sent Message IDs from this FIFO
  - number of used FIFO/Buffers
  - number of unused FIFO/Buffers


##### TX FIFO

* TX Queue with maximum size.
* Messages are sent in order of enqueue (i.e. circular buffer).
* Bus arbitrates according to Message ID (Frame ID).
* If more messages are enqueued than available, additional messages are discarded. Return behavior:
  - Status code like TX Overflow
  - List of discarded Message ID's (i.e. empty list == no overflow)
* Status message (on each BUS operation) includes:
  - list of sent Message IDs from this TX FIFO
  - number of used FIFO/Buffers
  - number of unused FIFO/Buffers


##### RX FIFO

* RX Queue with maximum size.
* Queue is cleared when ECU requests BUS Pull. ECU must handle all messages.
* Otherwise otherwise overflow condition can result.
  - Status code Rx Overflow.
* Status message (on each BUS operation) includes:
  - number of used FIFO/Buffers
  - number of unused FIFO/Buffers
* Filtering ... to be determined.



#### TEC


#### REC


#### Active Error Frame


#### Passive Error Frame


#### Overload


#### Frame Request


#### L2 Status
