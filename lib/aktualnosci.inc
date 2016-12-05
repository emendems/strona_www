<?php

function fetchAllNews($connectDB, $sort="desc"){ //wyswietlanie wszystkich aktualnosci
  $arrayNews = array();

if ($sort==null or ($sort!='asc' and $sort!='desc')){//domyślne sortowanie i sortowanie w przypadku wpisania głupoty
  $sort="desc";
}

  $sqlQuery = "SELECT * FROM t_aktualnosci ORDER BY data_publikacji_aktualnosci ".$sort;
  $sqlResult = mysqli_query($connectDB, $sqlQuery);
  $numRows = mysqli_num_rows($sqlResult);
    if($numRows>0){
      while($oneRow = mysqli_fetch_assoc($sqlResult)){ //podobnie jak foreach, wykonuje dopoki nie przejdzie po wszystkich rekordach
        $arrayNews[] = $oneRow;
      }
      return $arrayNews;
    }else{
      return 0; //brak aktualności
    }
}

function addNew($connectDB){ //dodawanie nowej aktualności
  $sqlQuery ="INSERT INTO t_aktualnosci (tytul_aktualnosci, naglowek_aktualnosci, data_publikacji_aktualnosci) VALUES ('Jak się robi pyszne jogurty?','Treść nowej aktualności',NOW())";

mysqli_query($connectDB, $sqlQuery);

}//koniec funkcji

?>
