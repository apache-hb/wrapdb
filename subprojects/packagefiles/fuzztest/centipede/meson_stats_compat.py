#!/usr/bin/env python3

import pathlib
import re
import sys


source = pathlib.Path(sys.argv[1]).read_text()
if sys.argv[1].endswith("stats.h"):
    source = source.replace(
        "uint64_t Stats::*field;",
        "uint64_t (*field)(const Stats &);",
    )
    field_names = re.findall(r"&Stats::([a-zA-Z0-9_]+),", source)
    accessors = "\n".join(
        f"  static uint64_t Get_{name}(const Stats &stats) {{ "
        f"return stats.{name}; }}"
        for name in field_names
    )
    source = source.replace(
        "  static constexpr std::initializer_list<FieldInfo> kFieldInfos = {",
        accessors
        + "\n\n  static constexpr std::initializer_list<FieldInfo> kFieldInfos = {",
    )
    source = re.sub(
        r"&Stats::([a-zA-Z0-9_]+),",
        r"&Stats::Get_\1,",
        source,
    )
else:
    source = source.replace(
        "stats_snapshots.at(idx).*(field_info.field)",
        "(field_info.field)(stats_snapshots.at(idx))",
    )
pathlib.Path(sys.argv[2]).write_text(source)
