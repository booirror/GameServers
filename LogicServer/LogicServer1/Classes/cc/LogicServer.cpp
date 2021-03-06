// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: LogicServer.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "LogicServer.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace protocol {

namespace {

const ::google::protobuf::Descriptor* CLogiCLogin_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  CLogiCLogin_reflection_ = NULL;
const ::google::protobuf::Descriptor* SLogiCLogin_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  SLogiCLogin_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_LogicServer_2eproto() {
  protobuf_AddDesc_LogicServer_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "LogicServer.proto");
  GOOGLE_CHECK(file != NULL);
  CLogiCLogin_descriptor_ = file->message_type(0);
  static const int CLogiCLogin_offsets_[3] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(CLogiCLogin, cmd_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(CLogiCLogin, servername_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(CLogiCLogin, seession_),
  };
  CLogiCLogin_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      CLogiCLogin_descriptor_,
      CLogiCLogin::default_instance_,
      CLogiCLogin_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(CLogiCLogin, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(CLogiCLogin, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(CLogiCLogin));
  SLogiCLogin_descriptor_ = file->message_type(1);
  static const int SLogiCLogin_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SLogiCLogin, cmd_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SLogiCLogin, err_),
  };
  SLogiCLogin_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      SLogiCLogin_descriptor_,
      SLogiCLogin::default_instance_,
      SLogiCLogin_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SLogiCLogin, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SLogiCLogin, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(SLogiCLogin));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_LogicServer_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    CLogiCLogin_descriptor_, &CLogiCLogin::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    SLogiCLogin_descriptor_, &SLogiCLogin::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_LogicServer_2eproto() {
  delete CLogiCLogin::default_instance_;
  delete CLogiCLogin_reflection_;
  delete SLogiCLogin::default_instance_;
  delete SLogiCLogin_reflection_;
}

void protobuf_AddDesc_LogicServer_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\021LogicServer.proto\022\010protocol\"F\n\013CLogicL"
    "ogin\022\021\n\003cmd\030\001 \001(\r:\0044096\022\022\n\nservername\030\002 "
    "\001(\t\022\020\n\010seession\030\003 \001(\t\"-\n\013SLogiCLogin\022\021\n\003"
    "cmd\030\001 \001(\r:\0044096\022\013\n\003err\030\002 \001(\r", 148);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "LogicServer.proto", &protobuf_RegisterTypes);
  CLogiCLogin::default_instance_ = new CLogiCLogin();
  SLogiCLogin::default_instance_ = new SLogiCLogin();
  CLogiCLogin::default_instance_->InitAsDefaultInstance();
  SLogiCLogin::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_LogicServer_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_LogicServer_2eproto {
  StaticDescriptorInitializer_LogicServer_2eproto() {
    protobuf_AddDesc_LogicServer_2eproto();
  }
} static_descriptor_initializer_LogicServer_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int CLogiCLogin::kCmdFieldNumber;
const int CLogiCLogin::kServernameFieldNumber;
const int CLogiCLogin::kSeessionFieldNumber;
#endif  // !_MSC_VER

CLogiCLogin::CLogiCLogin()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void CLogiCLogin::InitAsDefaultInstance() {
}

CLogiCLogin::CLogiCLogin(const CLogiCLogin& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void CLogiCLogin::SharedCtor() {
  _cached_size_ = 0;
  cmd_ = 4096u;
  servername_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  seession_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

CLogiCLogin::~CLogiCLogin() {
  SharedDtor();
}

void CLogiCLogin::SharedDtor() {
  if (servername_ != &::google::protobuf::internal::kEmptyString) {
    delete servername_;
  }
  if (seession_ != &::google::protobuf::internal::kEmptyString) {
    delete seession_;
  }
  if (this != default_instance_) {
  }
}

void CLogiCLogin::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* CLogiCLogin::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return CLogiCLogin_descriptor_;
}

const CLogiCLogin& CLogiCLogin::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_LogicServer_2eproto();
  return *default_instance_;
}

CLogiCLogin* CLogiCLogin::default_instance_ = NULL;

CLogiCLogin* CLogiCLogin::New() const {
  return new CLogiCLogin;
}

void CLogiCLogin::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    cmd_ = 4096u;
    if (has_servername()) {
      if (servername_ != &::google::protobuf::internal::kEmptyString) {
        servername_->clear();
      }
    }
    if (has_seession()) {
      if (seession_ != &::google::protobuf::internal::kEmptyString) {
        seession_->clear();
      }
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool CLogiCLogin::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional uint32 cmd = 1 [default = 4096];
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &cmd_)));
          set_has_cmd();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(18)) goto parse_servername;
        break;
      }

      // optional string servername = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_servername:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_servername()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->servername().data(), this->servername().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(26)) goto parse_seession;
        break;
      }

      // optional string seession = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_seession:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_seession()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->seession().data(), this->seession().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }

      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void CLogiCLogin::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional uint32 cmd = 1 [default = 4096];
  if (has_cmd()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->cmd(), output);
  }

  // optional string servername = 2;
  if (has_servername()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->servername().data(), this->servername().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      2, this->servername(), output);
  }

  // optional string seession = 3;
  if (has_seession()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->seession().data(), this->seession().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      3, this->seession(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* CLogiCLogin::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional uint32 cmd = 1 [default = 4096];
  if (has_cmd()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->cmd(), target);
  }

  // optional string servername = 2;
  if (has_servername()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->servername().data(), this->servername().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        2, this->servername(), target);
  }

  // optional string seession = 3;
  if (has_seession()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->seession().data(), this->seession().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        3, this->seession(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int CLogiCLogin::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional uint32 cmd = 1 [default = 4096];
    if (has_cmd()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->cmd());
    }

    // optional string servername = 2;
    if (has_servername()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->servername());
    }

    // optional string seession = 3;
    if (has_seession()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->seession());
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void CLogiCLogin::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const CLogiCLogin* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const CLogiCLogin*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void CLogiCLogin::MergeFrom(const CLogiCLogin& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_cmd()) {
      set_cmd(from.cmd());
    }
    if (from.has_servername()) {
      set_servername(from.servername());
    }
    if (from.has_seession()) {
      set_seession(from.seession());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void CLogiCLogin::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void CLogiCLogin::CopyFrom(const CLogiCLogin& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool CLogiCLogin::IsInitialized() const {

  return true;
}

void CLogiCLogin::Swap(CLogiCLogin* other) {
  if (other != this) {
    std::swap(cmd_, other->cmd_);
    std::swap(servername_, other->servername_);
    std::swap(seession_, other->seession_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata CLogiCLogin::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = CLogiCLogin_descriptor_;
  metadata.reflection = CLogiCLogin_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int SLogiCLogin::kCmdFieldNumber;
const int SLogiCLogin::kErrFieldNumber;
#endif  // !_MSC_VER

SLogiCLogin::SLogiCLogin()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void SLogiCLogin::InitAsDefaultInstance() {
}

SLogiCLogin::SLogiCLogin(const SLogiCLogin& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void SLogiCLogin::SharedCtor() {
  _cached_size_ = 0;
  cmd_ = 4096u;
  err_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

SLogiCLogin::~SLogiCLogin() {
  SharedDtor();
}

void SLogiCLogin::SharedDtor() {
  if (this != default_instance_) {
  }
}

void SLogiCLogin::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* SLogiCLogin::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return SLogiCLogin_descriptor_;
}

const SLogiCLogin& SLogiCLogin::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_LogicServer_2eproto();
  return *default_instance_;
}

SLogiCLogin* SLogiCLogin::default_instance_ = NULL;

SLogiCLogin* SLogiCLogin::New() const {
  return new SLogiCLogin;
}

void SLogiCLogin::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    cmd_ = 4096u;
    err_ = 0u;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool SLogiCLogin::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional uint32 cmd = 1 [default = 4096];
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &cmd_)));
          set_has_cmd();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(16)) goto parse_err;
        break;
      }

      // optional uint32 err = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_err:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &err_)));
          set_has_err();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }

      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void SLogiCLogin::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional uint32 cmd = 1 [default = 4096];
  if (has_cmd()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->cmd(), output);
  }

  // optional uint32 err = 2;
  if (has_err()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->err(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* SLogiCLogin::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional uint32 cmd = 1 [default = 4096];
  if (has_cmd()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->cmd(), target);
  }

  // optional uint32 err = 2;
  if (has_err()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->err(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int SLogiCLogin::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional uint32 cmd = 1 [default = 4096];
    if (has_cmd()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->cmd());
    }

    // optional uint32 err = 2;
    if (has_err()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->err());
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void SLogiCLogin::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const SLogiCLogin* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const SLogiCLogin*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void SLogiCLogin::MergeFrom(const SLogiCLogin& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_cmd()) {
      set_cmd(from.cmd());
    }
    if (from.has_err()) {
      set_err(from.err());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void SLogiCLogin::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void SLogiCLogin::CopyFrom(const SLogiCLogin& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool SLogiCLogin::IsInitialized() const {

  return true;
}

void SLogiCLogin::Swap(SLogiCLogin* other) {
  if (other != this) {
    std::swap(cmd_, other->cmd_);
    std::swap(err_, other->err_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata SLogiCLogin::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = SLogiCLogin_descriptor_;
  metadata.reflection = SLogiCLogin_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace protocol

// @@protoc_insertion_point(global_scope)
