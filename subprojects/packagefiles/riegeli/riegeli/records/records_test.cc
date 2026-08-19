#include <cstdio>
#include <string>

#include "riegeli/bytes/fd_reader.h"
#include "riegeli/bytes/fd_writer.h"
#include "riegeli/records/record_reader.h"
#include "riegeli/records/record_writer.h"

int main() {
  const char* path = "riegeli-records-test.riegeli";
  {
    riegeli::RecordWriter writer((riegeli::FdWriter(path)));
    if (!writer.WriteRecord("first") || !writer.WriteRecord("second") ||
        !writer.Close()) {
      return 1;
    }
  }

  riegeli::RecordReader reader((riegeli::FdReader(path)));
  std::string record;
  if (!reader.ReadRecord(record) || record != "first") return 2;
  if (!reader.ReadRecord(record) || record != "second") return 3;
  if (reader.ReadRecord(record) || !reader.ok()) return 4;
  if (!reader.Close()) return 5;
  return std::remove(path) == 0 ? 0 : 6;
}
