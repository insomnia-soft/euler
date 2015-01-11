<?php
	require "class_broj_en.php";
	
	$broj_slova = 0;

	for ($i = 1; $i <= 1000; $i++)
	{
		$klasa = new broj($i);
		$tekst = $klasa -> get_broj_slovima();
		
		for ($j = 0; $j < strlen($tekst); $j++)
		{
			$slovo = ord(substr($tekst, $j, 1));
			
			if ($slovo >= 97 && $slovo <= 122)
				$broj_slova++;
		}
	}
	
	echo "Broj slova: $broj_slova";

?>