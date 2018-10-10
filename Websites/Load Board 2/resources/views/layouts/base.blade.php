<!doctype html>
<html>
  <head>
    <title>{{ $page_title }}</title>
    @yield('head')
    @yield('styles')
  </head>
  <body>
    @yield('body')
  </body>
  @yield('scripts')
</html>
