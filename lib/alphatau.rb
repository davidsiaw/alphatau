require 'alphatau/version'
require 'singleton'

module Alphatau
  class Error < StandardError; end
  # Your code goes here...
  class Native
    include Singleton
  end
end

require 'alphatau/native'
