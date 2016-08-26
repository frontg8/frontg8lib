add_library(pb_protocol OBJECT
  frontg8/base.pb.cc
  frontg8/client.pb.cc
  frontg8/server.pb.cc
  )

include_directories(SYSTEM .)
install(DIRECTORY frontg8 DESTINATION include FILES_MATCHING PATTERN *.h)
