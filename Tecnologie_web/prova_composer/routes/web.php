<?php

use App\Http\Controllers\UserController;

Route::get('/', function () {
    return view('welcome');
});

Route::get('/hello', [UserController::class, 'sayHello']);

Route::get('/index', [UserController::class, 'index']);