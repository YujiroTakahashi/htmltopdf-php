--TEST--
htmltopdf() Basic test
--SKIPIF--
<?php
if (!extension_loaded('htmltopdf')) {
	echo 'skip';
}
?>
--FILE--
<?php
ob_start();
$size = html2pdf("https://www.yahoo.co.jp/");
ob_end_clean();

var_dump($size);
?>
--EXPECT--
int(128511)
