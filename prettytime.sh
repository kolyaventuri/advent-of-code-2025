#!/bin/sh
# Creates an MD compatible output from `time -l ./path/to/executable`

/usr/bin/time -l "$@" 2>&1 >/dev/null \
  | awk '
    /real/ { real=$1 }
    /user/ { user=$1 }
    /sys/  { sys=$1 }
    /maximum resident set size/ { rss=$1 }
    END {
      printf "### Performance\n"
      printf "- **Real**: %s sec\n", real
      printf "- **User**: %s sec\n", user
      printf "- **Sys**:  %s sec\n", sys
      printf "- **Peak RSS**: %.2f MB\n", rss/1024/1024
    }
  '
