dnl config.m4 for extension scream

PHP_ARG_ENABLE(scream, whether to enable scream support,
[  --enable-scream           Enable scream support])

if test "$PHP_SCREAM" != "no"; then
	
  scream_sources="scream.c "

  PHP_NEW_EXTENSION(scream, $scream_sources, $ext_shared)
fi
