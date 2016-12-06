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


function getOneNew( $connectDB, $idNew){
  $sqlQuery="SELECT * FROM t_aktualnosci WHERE id_aktualnosci =".$idNew;
  $sqlResult=mysqli_query($connectDB,$sqlQuery);

  $numRows = mysqli_num_rows($sqlResult);

    if($numRows>0){
      return mysqli_fetch_assoc($sqlResult);
    }else{
      return 0; //brak aktualności
    }
}//koniec funkcji



function addNew($connectDB, $dataFormNew){ //dodawanie nowej aktualności $dataFormNew to moje dane
//debug($dataFormNew); pokaże mi tablicę w surowej formie
  $sqlQuery ="INSERT INTO t_aktualnosci (tytul_aktualnosci, naglowek_aktualnosci, data_publikacji_aktualnosci) VALUES ('".$dataFormNew['tytul_aktualnosci']."','".$dataFormNew['naglowek_aktualnosci']."',"."NOW())";
  //można tu użyć backslasha. pojedyncze cudzysłowy to te, które będą zawarte w zapytaniu. podwójne są robocze
mysqli_query($connectDB, $sqlQuery);
//echo $sqlQuery;
}//koniec funkcji

function delete($connectDB, $id_aktualnosci){ //kasuje aktualność. $id_aktualności
  $sqlQuery ="DELETE FROM t_aktualnosci WHERE id_aktualnosci=$id_aktualnosci";
//echo $sqlQuery;
  mysqli_query($connectDB, $sqlQuery);
}//koniec funkcji

/*function update($connectDB, $dataFormNew){
  $sqlQuery ="UPDATE t_aktualnosci SET WHERE ;
  mysqli_query($connectDB, $sqlQuery);
}//koniec funkcji*/
?>
