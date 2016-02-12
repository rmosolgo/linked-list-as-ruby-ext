$LOAD_PATH << File.expand_path("../lib/", __FILE__)
require "linked_list/version"

Gem::Specification.new do |s|
  s.name        = "linked_list"
  s.version     = LinkedList::VERSION
  s.licenses    = ["MIT"]
  s.summary     = "A fast, immutable list for CRuby"
  s.description = "A fast, immutable list for Ruby, implemented in C"
  s.authors     = ["Robert Mosolgo"]
  s.email       = "rdmosolgo@gmail.com"
  s.homepage    = "https://rubygems.org/gems/example"

  s.add_development_dependency "rake-compiler"
end
