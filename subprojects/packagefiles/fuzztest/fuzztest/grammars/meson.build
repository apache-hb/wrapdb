json_grammar = custom_target(
  'fuzztest_json_grammar',
  input: 'JSON.g4',
  output: 'json_grammar.h',
  command: [
    grammar_domain_code_generator,
    '--top_level_rule',
    'json',
    '--input_grammar_files',
    '@INPUT@',
    '--output_header_file_path',
    '@OUTPUT@',
  ],
)
