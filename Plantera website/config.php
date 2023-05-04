<?php 

require __DIR__.'/vendor/autoload.php';

use Kreait\Firebase\Factory;
use Kreait\Firebase\Auth;

$factory = (new Factory)    
    ->withServiceAccount('plant-329fc-firebase-adminsdk-u1xtz-14de828fc9.json')
    ->withDatabaseUri('https://plant-329fc-default-rtdb.firebaseio.com/');
$database = $factory->createDatabase();
$auth = $factory->createAuth();
// session_start();
//

$dbURL = "https://trying-plantera-default-rtdb.firebaseio.com";

?>
