<?php

function fetchAllFoto($connectDB){
  $arrayFoto = array();

  $sqlQuery = "SELECT * FROM t_galeria;";
  $sqlResult = mysqli_query($connectDB, $sqlQuery);
  $numRows = mysqli_num_rows($sqlResult);
    if($numRows>0){
      while($oneRow = mysqli_fetch_assoc($sqlResult)){ //podobnie jak foreach, wykonuje dopoki nie przejdzie po wszystkich rekordach
        $arrayFoto[] = $oneRow;
      }
      return $arrayFoto;
    }else{
      return 0; //brak aktualności
    }
}

function getOnePhoto($connectDB, $id_photo){ //$id_photo to parametr funkcji
  $sqlQuery = "SELECT tytul_zdjecia, nazwa_zdjecia FROM t_galeria WHERE id_zdjecia=".$id_photo; //zapytanie sql
  $sqlResult = mysqli_query($connectDB, $sqlQuery); //wykonanie zapytania
  $numRows = mysqli_num_rows($sqlResult); //zwrotka o ilości rekordów
  if($numRows>0){ //sprawdzamy czy więcej niż 0
    //$oneRow = mysqli_fetch_row($sqlResult); //pobranie rekordu jednego zdjęcia w postaci tablicy autonumerycznej. fetch_assoc daje tablicę asocjacyjną
    //$oneRow = mysqli_fetch_assoc($sqlResult);
    return mysqli_fetch_assoc($sqlResult); //tablica z jednym zdjęciem
  }else{
    return 0; //brak zdjęć
  }//koniec sprawdzania

}//koniec funkcji

?>
