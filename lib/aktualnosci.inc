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

function addNewFoto($connectDB, $dataFormPhoto, $dataFilePhoto){ // 1. konektor, 2. tablica POST, 3. tablica FILE
    debug($dataFilePhoto);
    if(is_uploaded_file($dataFilePhoto["nazwa_zdjecia"]["tmp_name"]) == true){
    //echo $dataFilePhoto["nazwa_zdjecia"]["tmp_name"];
    $test=move_uploaded_file($dataFilePhoto["nazwa_zdjecia"]["tmp_name"], "img/".$dataFilePhoto["nazwa_zdjecia"]["name"]);
    //debug($test);
    if($test==true){
      $sqlQuery ="INSERT INTO t_galeria (tytul_zdjecia, nazwa_zdjecia) VALUES ('".$dataFormPhoto['tytul_zdjecia']."','"."img/".$dataFilePhoto['nazwa_zdjecia']["name"]."')";
      //echo $sqlQuery;
      mysqli_query($connectDB, $sqlQuery);
    }


    //echo $sqlQuery;
  }//koniec funkcji
}
function delete($connectDB, $id_aktualnosci){ //kasuje aktualność. $id_aktualności
  $sqlQuery ="DELETE FROM t_aktualnosci WHERE id_aktualnosci=$id_aktualnosci";
  //echo $sqlQuery;
  mysqli_query($connectDB, $sqlQuery);
  }//koniec funkcji

function deleteFoto($connectDB, $id_zdjecia, $nazwa_zdjecia){ //kasuje aktualność. $id_aktualności
    $sqlQuery ="DELETE FROM t_galeria WHERE id_zdjecia=$id_zdjecia";
    mysqli_query($connectDB, $sqlQuery);

    echo unlink($nazwa_zdjecia);

    }//koniec funkcji

function saveNew($connectDB, $dataFormNew){
  $dataNow = date("Y-m-d H:i:s"); //ustawia obecną godzinę
  $sqlQuery="UPDATE t_aktualnosci SET
  tytul_aktualnosci = '".$dataFormNew["tytul_aktualnosci"]."',
  naglowek_aktualnosci='".$dataFormNew["naglowek_aktualnosci"]."',
  data_publikacji_aktualnosci = '".$dataNow."'
  WHERE id_aktualnosci=".$_GET["id_new"]; //przekazane w pasku z formularza <edycja aktualnosci> w pliku update.php
  mysqli_query($connectDB, $sqlQuery);
}

function saveNewFoto($connectDB, $dataFormPhoto, $dataFilePhoto){
  //debug($dataFormPhoto);

    if(is_uploaded_file($dataFilePhoto["nazwa_zdjecia"]["tmp_name"]) == true){

      $test=move_uploaded_file($dataFilePhoto["nazwa_zdjecia"]["tmp_name"], "img/".$dataFilePhoto["nazwa_zdjecia"]["name"]);

        if($test==true){
          $testUnlink = unlink($dataFormPhoto["nazwa_zdjecia_old"]); //wyrzucam zdjęcie z folderu

          if($testUnlink==true){ //jeśli zdjęcie wyrzuciło się z folderu, to podmieniam je w bazie
                $sqlQuery="UPDATE t_galeria SET
                tytul_zdjecia = '".$dataFormPhoto["tytul_zdjecia"]."',
                nazwa_zdjecia='img/".$dataFilePhoto["nazwa_zdjecia"]["name"]."'
                WHERE id_zdjecia=".$_GET["idPhoto"]; //przekazane w pasku z formularza <edycja aktualnosci> w pliku update.php
                mysqli_query($connectDB, $sqlQuery);
}

} else{
  $sqlQuery="UPDATE t_galeria SET
      tytul_zdjecia = '".$dataFormPhoto["tytul_zdjecia"]."'
      WHERE id_zdjecia=".$_GET["idPhoto"];
      echo $sqlQuery;
      //mysqli_query($connectDB, $sqlQuery);
}}}
?>
