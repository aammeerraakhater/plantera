<?php
  $style = "showaccs.css";
  include 'init.php';
  require 'topNav.php';
?>
<div class="container showaccsCon">
  <h2>Plantera members</h2>
<table class="table">
  <thead>
    <tr>
      <th scope="col">#</th>
      <th scope="col">Name</th>
      <th scope="col">Email</th>
      <th scope="col">Phone</th>
      <th scope="col">Number of farms</th>
      <th scope="col">Edit</th>
      <th scope="col">Delete</th>

    </tr>
  </thead>
  <tbody>
    <tr>
      <th scope="row">1</th>
      <td>Mark Otto</td>
      <td>@mdo</td>
      <td>@mdo</td>
      <td>4</td>
      <td><button type="button" class="btn btn-info">Edit</button></td>
      <td><button type="button" class="btn btn-danger">Delete</button></td>

    </tr>
    <tr>
      <th scope="row">2</th>
      <td>Jacob Thornton</td>
      <td>@fat</td>
      <td>@fat</td>
      <td>6</td>
      <td><button type="button" class="btn btn-info">Edit</button></td>
      <td><button type="button" class="btn btn-danger">Delete</button></td>

    </tr>
    <tr>
      <th scope="row">3</th>
      <td>Larry the Bird</td>
      <td>@twitter</td>
      <td>@twitter</td>
      <td>2</td>
      <td><button type="button" class="btn btn-info">Edit</button></td>
      <td><button type="button" class="btn btn-danger">Delete</button></td>
    </tr>
  </tbody>
</table>
</div>
