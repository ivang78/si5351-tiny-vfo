<?php

if (isset ($argv[1]) && $argv[1]) {
	$filename = $argv[1];
	echo "Filename: ".$filename."\n";
	$fp1 = fopen($filename, "r");
	$fp2 = fopen($filename.".conv", "w");	
	while(!feof($fp1)) {
  		$str = fgets($fp1);
  		if (strpos ($str, "0x") !== false && substr_count ($str, ",") == 16) {
  			$arr = explode (",", $str);
  			$arr2 = array ();
  			$rest_str = "";
  			foreach ($arr as $_i => $hexv) {
  				if ($_i <= 15) {
	  				$binv = str_pad (base_convert(str_replace ("0x", "", $hexv), 16, 2), 8, "0", STR_PAD_LEFT);
	  				$arr2[$_i] = $binv;
	  			} else {
	  				$rest_str .= $hexv;
	  			}
  			}
  			$arr3 = array ();
  			for ($_i = 0; $_i <=7; $_i++) {
  				$str2 = "";
  				foreach ($arr2 as $binv) {
					$str2 = substr ($binv, $_i, 1).$str2;
				}
				$arr3[$_i] = substr ($str2, 7, 8);
				$arr3[$_i + 8] = substr ($str2, 0, 8);
  			}
  			ksort($arr3);
  			$arr4 = array ();
  			foreach ($arr3 as $binv) {
				$arr4[] = "0x".str_pad (base_convert($binv, 2, 16), 2, "0", STR_PAD_LEFT);
			}
			$arr4[] = $rest_str;
			$str = implode (",", $arr4)."\n";
  		}
  		fputs ($fp2, $str);
	}
	fclose ($fp1);
	fclose ($fp2);
} else {
	echo "Error\n";
}