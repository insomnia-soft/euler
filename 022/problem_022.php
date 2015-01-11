<?php
	$fp = fopen("names.txt", "r");
	
	if ($fp)
		echo "file opened!<br />";
	else
		echo "file open fail!<br />";
	
	$input = fgets($fp);
	
	fclose($fp);
	
	$input = str_replace(",\"", "", $input);
	$input = substr($input, 1, strlen($input) - 2);
	
	$name = explode("\"", $input);
	
	sort($name);
	
	echo "name[938 - 1] = " . $name[937] . "<br /><br />";

	$totalsum = 0;
	
	foreach ($name as $key => $value)
	{
		$sum = 0;
		
		for ($i = 0; $i < strlen($value); $i++)
			$sum = $sum + ord(substr($value, $i, 1)) - 64;
		
		$totalsum += ($key + 1) * $sum;
	}
		
	echo $totalsum;
?>