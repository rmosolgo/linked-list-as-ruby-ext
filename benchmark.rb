$LOAD_PATH << File.expand_path("../lib/", __FILE__)

require "benchmark"
require "linked_list"
require "hamster"

TIMES = 500

def test_hamster
  list = Hamster::List[]

  TIMES.times do |x|
    list = list.add(x)
  end
  TIMES.times do |x|
    list = list << x
  end

  list.each { |el| el }

  TIMES.times do |x|
    list.first
    list = list.pop
  end

  TIMES.times do |x|
    list.last
    list = list.drop(1)
  end
end

def test_linked_list
  list = LinkedList.new

  TIMES.times do |x|
    list = list.unshift(x)
  end

  TIMES.times do |x|
    list = list.push(x)
  end

  list.each { |el| el }

  TIMES.times do |x|
    list.first
    list = list.pop
  end

  TIMES.times do |x|
    list.last
    list = list.shift
  end
end


Benchmark.bm(12) do |x|
  x.report("Hamster::List") { test_hamster }
  x.report("LinkedList") { test_linked_list }
end
