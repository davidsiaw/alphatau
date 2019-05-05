require 'mkmf'

ext_name = 'native'

dir_config('alphatau/native')

system("cd #{$srcdir}/sdl && ./configure --prefix=`pwd` --enable-shared=no && make install")

required_funcs = %w[]

$CPPFLAGS << ' ' + `#{$srcdir}/sdl/bin/sdl2-config --cflags`.chomp
$LDFLAGS << ' ' + `#{$srcdir}/sdl/bin/sdl2-config --static-libs`.chomp

required_funcs.each do |funcname|
  abort "missing #{funcname}()" unless have_func funcname
end

create_makefile ext_name
