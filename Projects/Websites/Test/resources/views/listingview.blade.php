@extends('masterview')

@section('body')
  <h2><b>This is the testing page for a listing for my site.</b></h2>
  @foreach ($listings as $listing)
    {!! $listing->toHTML() !!}
  @endforeach
@endsection
