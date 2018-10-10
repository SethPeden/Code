@extends('layouts.base')

@section('styles')

  <style>
  .header {
    background-color: rgb(255, 0, 0);
  }
  .header-text {
    color: rgb(255, 255, 255);
  }
  .spacer {
    width: 100%;
  }
  .row {
    white-space: nowrap;
  }
  </style>

@endsection('styles')

@section('scripts')

@endsection('scripts')

@section('content')

  <header class='header'>
    <div class='row'>
      <span class='spacer'>Hey</span>
      <h1 class='header-text'>Load Board</h1>
    </div>
  </header>

@endsection('content')
