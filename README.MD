
Base on https://pecl.php.net/package/scream fix for php7

# Build

```
$ phpize
$ ./configure
$ make
$ make install
```

- Enable it in `.ini`

- Run test `php -dscream.enabled=1 program.php`
