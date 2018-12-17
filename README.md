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
ob_start();
$size = html2pdf("https://www.yahoo.co.jp/");
$buf = ob_get_clean();

if (0 != $err_code) {
  exit('error:'.$err_code);
}

header('Content-Type: application/pdf');
header('Content-Length: '. $size);
header('Content-Disposition: attachment; filename="yahoo.pdf"');
echo $size;
```

-----
