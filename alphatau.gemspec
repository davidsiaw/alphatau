lib = File.expand_path('lib', __dir__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require 'alphatau/version'

Gem::Specification.new do |spec|
  spec.name          = 'alphatau'
  spec.version       = Alphatau::VERSION
  spec.authors       = ['David Siaw']
  spec.email         = ['davidsiaw@gmail.com']

  spec.summary       = 'SDL gem for ruby'
  spec.description   = 'SDL gem for ruby'
  spec.homepage      = 'https://github.com/davidsiaw/alphatau/'
  spec.license       = 'MIT'

  # Prevent pushing this gem to RubyGems.org. To allow pushes either set the
  # 'allowed_push_host' to allow pushing to a single host or delete this section
  # to allow pushing to any host.
  if spec.respond_to?(:metadata)
    spec.metadata['allowed_push_host'] = 'https://rubygems.org'

    spec.metadata['homepage_uri'] = spec.homepage
    spec.metadata['source_code_uri'] = 'https://github.com/davidsiaw/alphatau/'
    spec.metadata['changelog_uri'] = 'https://github.com/davidsiaw/alphatau/'
  else
    raise 'RubyGems 2.0 or newer is required to protect against ' \
      'public gem pushes.'
  end

  spec.files         = Dir['lib/**/*.rb'] +
                       Dir['bin/*'] +
                       Dir['ext/**/*'] +
                       Dir['data/**/*'] +
                       ['Rakefile']
  spec.bindir        = 'exe'
  spec.executables   = spec.files.grep(%r{^exe/}) { |f| File.basename(f) }
  spec.require_paths = ['lib']
  spec.extensions    = %w[ext/alphatau/native/extconf.rb]

  spec.add_development_dependency 'bundler', '~> 2.0'
  spec.add_development_dependency 'rake', '~> 10.0'
  spec.add_development_dependency 'rake-compiler'
  spec.add_development_dependency 'rspec', '~> 3.0'
end
