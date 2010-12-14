deeploveLib.php
code
php testWeb

<?php
$link=mysql_connect("localhost","","");
if(!$link) {
	print("Failed to establish connection to mysql server!");
	exit();
}
//Select the database
$status=mysql_select_db("deeplovelib");

// insert data
if($_POST["title"]) {
	mysql_query("INSERT INTO DataTable
	(title, tag, content) VALUES('$_POST[title]', '$_POST[tag]', 'log' ) ")
	or die(mysql_error());
	exit();
}


$query="SELECT * FROM DataTable";
$result=mysql_query($query);
if(!$result) {
	print("Query Error: ".mysql_error());
}
//$numrows=mysql_num_rows($result);
//print("Number of rows returned: $numrows <br />");
//while($row = mysql_fetch_array($result)){
//	echo $row['title'];
//	echo "<br />";
//}

//$jsonData = array(array("title"=>"test1"), array("title"=>"test2"));
//echo json_encode($jsonData)


$rows = array();
while($r = mysql_fetch_assoc($result)) {
    $rows[] = $r;
}

echo json_encode($rows)




?>

<?
//php echo $_POST["queryStr"];
 ?>

