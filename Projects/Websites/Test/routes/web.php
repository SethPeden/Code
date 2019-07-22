<?php

/*
|--------------------------------------------------------------------------
| Web Routes
|--------------------------------------------------------------------------
|
| Here is where you can register web routes for your application. These
| routes are loaded by the RouteServiceProvider within a group which
| contains the "web" middleware group. Now create something great!
|
*/

use App\Listing;

Route::get('/', function () {
    return View('index');
});

Route::get('/listing', function() {
  $listings = array();
  $listings[] = new Listing('Lamp', 'This is a very nice lamp.', 29.99);
  $listings[] = new Listing('Stand', 'This will never fall down.', 14.99);
  $listings[] = new Listing('Book', 'You\'ll never put it down!', 6.99);
  return View('listingview', ['listings' => $listings]);
});
