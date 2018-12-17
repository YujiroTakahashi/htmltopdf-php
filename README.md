# htmltopdf-php
 PHP bindings for wkhtmltox.

[wk html to x](https://wkhtmltopdf.org/) a Morphological Analyzer Toolkit.

## Requirements

libwkhtmltox


## Building htmltopdf for PHP

```
$ cd htmltopdf-php
$ phpize
$ ./configure
$ make
$ sudo make install
```


edit your php.ini and add:

-----

### <a name="__construct">int html2pdf(string url, string output)

```php
$buf = html2pdf("https://www.yahoo.co.jp/");

header('Content-Type: application/pdf');
header('Content-Length: '. strlen($buf));
header('Content-Disposition: attachment; filename="yahoo.pdf"');
echo $buf;
```

-----
