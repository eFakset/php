 <?php
 
//phpinfo();

if (!function_exists('mysqli_init') && !extension_loaded('mysqli'))
{
    echo 'We don\'t have mysqli!!!<br/>';
    $loaded = get_loaded_extensions();
    for ($i = 0; $i < count($loaded); $i++)
    	echo $loaded[$i] . "<br/>";
}
else
{
    echo 'Phew we have it!<br/>';

    $servername = "localhost";
    $username = "root";
    $password = "xxxxxxxx";
    $dbname = "slekt";

    // Create connection
    $conn = new mysqli($servername, $username, $password, $dbname);
    // Check connection
    if ($conn->connect_error) {
      die("Connection failed: " . $conn->connect_error);
    }

    $sql = "SELECT id, name FROM eventtype";
    $result = $conn->query($sql);

    if ($result->num_rows > 0)
    {
      // output data of each row
      	while($row = $result->fetch_assoc())
        	echo "id: " . $row["id"]. " - Name: " . $row["name"]. "<br>";
    }
    else
      	echo "0 results";

    $conn->close();
}
echo "SLUTT";
?>