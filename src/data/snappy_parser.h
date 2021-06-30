/**
 * @file   snappy_parser.h
 * @brief  parser for compressed row block data format
 */
#pragma once
#include "data/parser.h"
#include "dmlc/recordio.h"
namespace dmlc {
namespace data {

template <typename IndexType>
class SnappyParser : public ParserImpl<IndexType> {
 public:
  explicit SnappyParser(InputSplit *source)
      : bytes_read_(0), source_(source) {
  }

  virtual ~CRBParser() { delete source_; }

  virtual void BeforeFirst(void) {
    source_->BeforeFirst();
  }
  virtual size_t BytesRead(void) const {
    return bytes_read_;
  }


  virtual bool ParseNext(std::vector<RowBlockContainer<IndexType> > *data) {
    InputSplit::Blob rec;
    if (!source_->NextRecord(&rec)) return false;
    CHECK_NE(rec.size, 0);
    bytes_read_ += rec.size;

    data->resize(1); (*data)[0].Clear();
    //SnappyRowBlock srb;
    //srb.Decompress((char const*)rec.dptr, rec.size, &(*data)[0]);

    std::cout << "data:\n" << rec.dptr << std::endl;

    return true;
  }

 private:
  // number of bytes readed
  size_t bytes_read_;
  // source split that provides the data
  InputSplit *source_;
};

} // namespace data
} // namespace dmlc
