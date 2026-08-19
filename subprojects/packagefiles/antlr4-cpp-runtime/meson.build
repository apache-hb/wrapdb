project(
  'antlr4-cpp-runtime',
  'cpp',
  version: '4.13.2',
  meson_version: '>=0.59.0',
  default_options: ['cpp_std=c++17', 'warning_level=2'],
  license: 'BSD-3-Clause',
)

tests_opt = get_option('tests').disable_auto_if(meson.is_subproject())
threads = dependency('threads')

runtime_source_names = [
  'ANTLRErrorListener.cpp',
  'ANTLRErrorStrategy.cpp',
  'ANTLRFileStream.cpp',
  'ANTLRInputStream.cpp',
  'BailErrorStrategy.cpp',
  'BaseErrorListener.cpp',
  'BufferedTokenStream.cpp',
  'CharStream.cpp',
  'CommonToken.cpp',
  'CommonTokenFactory.cpp',
  'CommonTokenStream.cpp',
  'ConsoleErrorListener.cpp',
  'DefaultErrorStrategy.cpp',
  'DiagnosticErrorListener.cpp',
  'Exceptions.cpp',
  'FailedPredicateException.cpp',
  'InputMismatchException.cpp',
  'IntStream.cpp',
  'InterpreterRuleContext.cpp',
  'Lexer.cpp',
  'LexerInterpreter.cpp',
  'LexerNoViableAltException.cpp',
  'ListTokenSource.cpp',
  'NoViableAltException.cpp',
  'Parser.cpp',
  'ParserInterpreter.cpp',
  'ParserRuleContext.cpp',
  'ProxyErrorListener.cpp',
  'RecognitionException.cpp',
  'Recognizer.cpp',
  'RuleContext.cpp',
  'RuleContextWithAltNum.cpp',
  'RuntimeMetaData.cpp',
  'Token.cpp',
  'TokenSource.cpp',
  'TokenStream.cpp',
  'TokenStreamRewriter.cpp',
  'UnbufferedCharStream.cpp',
  'UnbufferedTokenStream.cpp',
  'Vocabulary.cpp',
  'WritableToken.cpp',
  'atn/ATN.cpp',
  'atn/ATNConfig.cpp',
  'atn/ATNConfigSet.cpp',
  'atn/ATNDeserializationOptions.cpp',
  'atn/ATNDeserializer.cpp',
  'atn/ATNSimulator.cpp',
  'atn/ATNState.cpp',
  'atn/ATNStateType.cpp',
  'atn/ActionTransition.cpp',
  'atn/AmbiguityInfo.cpp',
  'atn/ArrayPredictionContext.cpp',
  'atn/AtomTransition.cpp',
  'atn/ContextSensitivityInfo.cpp',
  'atn/DecisionEventInfo.cpp',
  'atn/DecisionInfo.cpp',
  'atn/DecisionState.cpp',
  'atn/EpsilonTransition.cpp',
  'atn/ErrorInfo.cpp',
  'atn/LL1Analyzer.cpp',
  'atn/LexerATNConfig.cpp',
  'atn/LexerATNSimulator.cpp',
  'atn/LexerAction.cpp',
  'atn/LexerActionExecutor.cpp',
  'atn/LexerChannelAction.cpp',
  'atn/LexerCustomAction.cpp',
  'atn/LexerIndexedCustomAction.cpp',
  'atn/LexerModeAction.cpp',
  'atn/LexerMoreAction.cpp',
  'atn/LexerPopModeAction.cpp',
  'atn/LexerPushModeAction.cpp',
  'atn/LexerSkipAction.cpp',
  'atn/LexerTypeAction.cpp',
  'atn/LookaheadEventInfo.cpp',
  'atn/NotSetTransition.cpp',
  'atn/OrderedATNConfigSet.cpp',
  'atn/ParseInfo.cpp',
  'atn/ParserATNSimulator.cpp',
  'atn/PrecedencePredicateTransition.cpp',
  'atn/PredicateEvalInfo.cpp',
  'atn/PredicateTransition.cpp',
  'atn/PredictionContext.cpp',
  'atn/PredictionContextCache.cpp',
  'atn/PredictionContextMergeCache.cpp',
  'atn/PredictionMode.cpp',
  'atn/ProfilingATNSimulator.cpp',
  'atn/RangeTransition.cpp',
  'atn/RuleTransition.cpp',
  'atn/SemanticContext.cpp',
  'atn/SetTransition.cpp',
  'atn/SingletonPredictionContext.cpp',
  'atn/StarLoopbackState.cpp',
  'atn/Transition.cpp',
  'atn/TransitionType.cpp',
  'atn/WildcardTransition.cpp',
  'dfa/DFA.cpp',
  'dfa/DFASerializer.cpp',
  'dfa/DFAState.cpp',
  'dfa/LexerDFASerializer.cpp',
  'internal/Synchronization.cpp',
  'misc/InterpreterDataReader.cpp',
  'misc/Interval.cpp',
  'misc/IntervalSet.cpp',
  'misc/MurmurHash.cpp',
  'misc/Predicate.cpp',
  'support/Any.cpp',
  'support/Arrays.cpp',
  'support/CPPUtils.cpp',
  'support/StringUtils.cpp',
  'support/Utf8.cpp',
  'tree/ErrorNodeImpl.cpp',
  'tree/IterativeParseTreeWalker.cpp',
  'tree/ParseTree.cpp',
  'tree/ParseTreeListener.cpp',
  'tree/ParseTreeVisitor.cpp',
  'tree/ParseTreeWalker.cpp',
  'tree/TerminalNodeImpl.cpp',
  'tree/Trees.cpp',
  'tree/pattern/Chunk.cpp',
  'tree/pattern/ParseTreeMatch.cpp',
  'tree/pattern/ParseTreePattern.cpp',
  'tree/pattern/ParseTreePatternMatcher.cpp',
  'tree/pattern/RuleTagToken.cpp',
  'tree/pattern/TagChunk.cpp',
  'tree/pattern/TextChunk.cpp',
  'tree/pattern/TokenTagToken.cpp',
  'tree/xpath/XPath.cpp',
  'tree/xpath/XPathElement.cpp',
  'tree/xpath/XPathLexer.cpp',
  'tree/xpath/XPathLexerErrorListener.cpp',
  'tree/xpath/XPathRuleAnywhereElement.cpp',
  'tree/xpath/XPathRuleElement.cpp',
  'tree/xpath/XPathTokenAnywhereElement.cpp',
  'tree/xpath/XPathTokenElement.cpp',
  'tree/xpath/XPathWildcardAnywhereElement.cpp',
  'tree/xpath/XPathWildcardElement.cpp',
]

runtime_sources = []
foreach path : runtime_source_names
  runtime_sources += files('runtime/src' / path)
endforeach

runtime_inc = include_directories('runtime/src')
cpp = meson.get_compiler('cpp')
cpp_args = cpp.get_supported_arguments(
  '-Wno-multichar',
  '-Wno-overloaded-virtual',
  '-Wno-dollar-in-identifier-extension',
  '-Wno-four-char-constants',
  '/wd4251',
)

if host_machine.system() == 'windows'
  if get_option('default_library') == 'static'
    cpp_args += ['-DANTLR4CPP_STATIC']
  else
    cpp_args += ['-DANTLR4CPP_EXPORTS']
  endif
endif

antlr4_runtime = library(
  'antlr4-runtime',
  runtime_sources,
  cpp_args: cpp_args,
  include_directories: runtime_inc,
  dependencies: threads,
  install: true,
  version: meson.project_version(),
)

antlr4_runtime_dep = declare_dependency(
  compile_args: host_machine.system() == 'windows' and get_option(
    'default_library',
  ) == 'static' ? [
    '-DANTLR4CPP_STATIC',
  ] : [],
  include_directories: runtime_inc,
  link_with: antlr4_runtime,
  dependencies: threads,
)

meson.override_dependency('antlr4-runtime', antlr4_runtime_dep)

install_subdir(
  'runtime/src',
  install_dir: get_option('includedir') / 'antlr4-runtime',
  strip_directory: true,
  exclude_directories: ['.idea'],
  exclude_files: runtime_source_names,
)

gtest_main = dependency(
  'gtest_main',
  required: tests_opt,
)

if gtest_main.found()
  antlr4_tests = executable(
    'antlr4_tests',
    'runtime/tests/Utf8Test.cpp',
    dependencies: [antlr4_runtime_dep, gtest_main],
    build_by_default: false,
  )
  test(
    'antlr4_tests',
    antlr4_tests,
    suite: 'antlr4-cpp-runtime',
  )
endif
