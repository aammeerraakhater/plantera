<?php 

require __DIR__.'/vendor/autoload.php';

use Kreait\Firebase\Factory;
use Kreait\Firebase\Auth;

$factory = (new Factory)    
    ->withServiceAccount('trying-plantera-firebase-adminsdk-xw684-cc787ed4cb.json')
    ->withDatabaseUri('https://trying-plantera-default-rtdb.firebaseio.com/');
$database = $factory->createDatabase();
$auth = $factory->createAuth();
// session_start();
//

$dbURL = "https://trying-plantera-default-rtdb.firebaseio.com";

?>
