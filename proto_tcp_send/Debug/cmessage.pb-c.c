/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: cmessage.proto */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C__NO_DEPRECATED
#define PROTOBUF_C__NO_DEPRECATED
#endif

#include "cmessage.pb-c.h"
void   submessage__init
                     (Submessage         *message)
{
  static Submessage init_value = SUBMESSAGE__INIT;
  *message = init_value;
}
size_t submessage__get_packed_size
                     (const Submessage *message)
{
  assert(message->base.descriptor == &submessage__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t submessage__pack
                     (const Submessage *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &submessage__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t submessage__pack_to_buffer
                     (const Submessage *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &submessage__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Submessage *
       submessage__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Submessage *)
     protobuf_c_message_unpack (&submessage__descriptor,
                                allocator, len, data);
}
void   submessage__free_unpacked
                     (Submessage *message,
                      ProtobufCAllocator *allocator)
{
  assert(message->base.descriptor == &submessage__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   emessage__init
                     (EMessage         *message)
{
  static EMessage init_value = EMESSAGE__INIT;
  *message = init_value;
}
size_t emessage__get_packed_size
                     (const EMessage *message)
{
  assert(message->base.descriptor == &emessage__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t emessage__pack
                     (const EMessage *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &emessage__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t emessage__pack_to_buffer
                     (const EMessage *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &emessage__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
EMessage *
       emessage__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (EMessage *)
     protobuf_c_message_unpack (&emessage__descriptor,
                                allocator, len, data);
}
void   emessage__free_unpacked
                     (EMessage *message,
                      ProtobufCAllocator *allocator)
{
  assert(message->base.descriptor == &emessage__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
static const ProtobufCFieldDescriptor submessage__field_descriptors[1] =
{
  {
    "value",
    1,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Submessage, value),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned submessage__field_indices_by_name[] = {
  0,   /* field[0] = value */
};
static const ProtobufCIntRange submessage__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 1 }
};
const ProtobufCMessageDescriptor submessage__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "Submessage",
  "Submessage",
  "Submessage",
  "",
  sizeof(Submessage),
  1,
  submessage__field_descriptors,
  submessage__field_indices_by_name,
  1,  submessage__number_ranges,
  (ProtobufCMessageInit) submessage__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor emessage__field_descriptors[1] =
{
  {
    "a",
    1,
    PROTOBUF_C_LABEL_REPEATED,
    PROTOBUF_C_TYPE_MESSAGE,
    offsetof(EMessage, n_a),
    offsetof(EMessage, a),
    &submessage__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned emessage__field_indices_by_name[] = {
  0,   /* field[0] = a */
};
static const ProtobufCIntRange emessage__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 1 }
};
const ProtobufCMessageDescriptor emessage__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "EMessage",
  "EMessage",
  "EMessage",
  "",
  sizeof(EMessage),
  1,
  emessage__field_descriptors,
  emessage__field_indices_by_name,
  1,  emessage__number_ranges,
  (ProtobufCMessageInit) emessage__init,
  NULL,NULL,NULL    /* reserved[123] */
};
