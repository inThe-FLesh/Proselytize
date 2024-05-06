project('proselytize', 'cpp', 'c', version: '0.1')
src = ['src/main.cpp', 'src/file_validation.cpp', 'src/AV_Extraction.cpp']

include = include_directories('include')

libavformat_dep = dependency('libavformat')

executable(
  'proselytize', 
  src, 
  include_directories: include,
  dependencies : libavformat_dep
  )
