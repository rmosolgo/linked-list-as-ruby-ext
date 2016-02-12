require 'bundler/setup'
require 'rake/extensiontask'
require 'rake/testtask'

Bundler::GemHelper.install_tasks

Rake::TestTask.new do |t|
  t.libs << 'test'
end

Rake::ExtensionTask.new "linked_list" do |ext|
  ext.lib_dir = "lib/linked_list"
end

task default: [:clean, :compile, :test]
