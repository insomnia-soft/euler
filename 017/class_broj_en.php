<?php
	class broj
	{
		private $broj;
	
		public function __construct($broj)
		{
			$this -> broj = (string) $broj;
		}
		
		private function tekst_broj($num)
		{
			$ret = "";
			
			if (strlen($num) == 3)
			{
				$jedinica = substr($num, strlen($num) - 1, 1);
				$desetica = substr($num, strlen($num) - 2, 1);
				
				switch (substr($num, strlen($num) - 3, 1))
				{
					case "1":	$ret = "one hundret";		break;
					case "2":	$ret = "two hundret";		break;
					case "3":	$ret = "three hundret";		break;
					case "4":	$ret = "four hundret";		break;
					case "5":	$ret = "five hundret";		break;
					case "6":	$ret = "six hundret";		break;
					case "7":	$ret = "seven hundret";		break;
					case "8":	$ret = "eight hundret";		break;
					case "9":	$ret = "nine hundret";		break;
					default:	$ret = "";					break;
				}
				
				if ($jedinica != "0" || $desetica != "0")
					$ret .= " and ";
			}
			
			if (strlen($num) >= 2)
			{
				$jedinica = substr($num, strlen($num) - 1, 1);
				$desetica = substr($num, strlen($num) - 2, 1);
			
				if ($desetica == "1")
				{
					switch ($jedinica)
					{
						case "0":	$ret .= "ten";				break;
						case "1":	$ret .= "eleven";			break;
						case "2":	$ret .= "twelve";			break;
						case "3":	$ret .= "thriteen";			break;
						case "4":	$ret .= "fourteen";			break;
						case "5":	$ret .= "fifteen";			break;
						case "6":	$ret .= "sixteen";			break;
						case "7":	$ret .= "seventeen";		break;
						case "8":	$ret .= "eighteen";			break;
						case "9":	$ret .= "nineteen";			break;
						default:	$ret .= "";					break;
					}
				}
				else
				{
					switch ($desetica)
					{
						case "2":
							if ($jedinica == "0")
								$ret .= "twelve";
							else
								$ret .= "twenty";
							
							break;
							
						case "3":	$ret .= "thirty";			break;
						case "4":	$ret .= "forty";			break;
						case "5":	$ret .= "fifty";			break;
						case "6":	$ret .= "sixty";			break;
						case "7":	$ret .= "seventy";			break;
						case "8":	$ret .= "eighty";			break;
						case "9":	$ret .= "ninety";			break;
						default:	$ret .= "";					break;
					}
				}
			}

			if (strlen($num) >= 1 && !(strlen($num) >= 2 && substr($num, strlen($num) - 2, 1) == "1"))
			{
				switch (substr($num, strlen($num) - 1, 1))
				{
					case "0":	$ret .= (strlen($num) > 1 ? "" : "zero");			break;
					case "1":	$ret .= "one";										break;
					case "2":	$ret .= "two";										break;
					case "3":	$ret .= "three";									break;
					case "4":	$ret .= "four";										break;
					case "5":	$ret .= "five";										break;
					case "6":	$ret .= "six";										break;
					case "7":	$ret .= "seven";									break;
					case "8":	$ret .= "eight";									break;
					case "9":	$ret .= "nine";										break;
					default:	$ret .= "";											break;
				}
			}
			
			return $ret;
		}
				
		public function get_broj_slovima()
		{
			$len = strlen($this -> broj);
			
			if ($len >= 1 && $len <= 3)
			{
				return $this -> tekst_broj($this -> broj);
			}
			elseif ($len == "4" && $this -> broj == "1000");
				return "one thousand";
		}
	}
?>