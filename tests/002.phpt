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
$buf = html2pdf("https://www.yahoo.co.jp/");
file_put_contents('./yahoo.pdf', $buf);

if (strlen($buf) !== 0) {
	echo "ok";
} else {
	echo "ng";
}
?>
--EXPECT--
ok
