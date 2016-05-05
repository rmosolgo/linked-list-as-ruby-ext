require "test_helper"

describe LinkedList do
  describe "#length" do
    it "defaults to 0" do
      list = LinkedList.new
      assert_equal 0, list.length
    end

    it "initializes with length" do
      list = LinkedList.new(:a, :b, :c)
      assert_equal 3, list.length
    end
  end

  describe "#each" do
    describe "when no members" do
      it "yields zero times" do
        list = LinkedList.new
        yields = []
        list.each { |item| yields << item }
        assert_equal([], yields)
      end
    end

    describe "when there are members" do
      it "yields the members in order" do
        list = LinkedList.new(1, nil, false, 0, true)
        yields = []
        list.each { |item| yields << item }
        assert_equal([1, nil, false, 0, true], yields)
      end
    end
  end

  describe "the front of the list" do
    describe "#first" do
      it "returns the first item" do
        list = LinkedList.new(:a, :b, :c)
        assert_equal(:a, list.first)
      end

      describe "when the list is empty" do
        it "returns nil" do
          list = LinkedList.new
          assert_equal nil, list.first
        end
      end
    end

    describe "#shift" do
      it "returns a new list without the first item" do
        list = LinkedList.new(nil, nil, nil, 1)
        assert_equal [nil, nil, 1], list.shift.to_a
        assert_equal [nil, 1], list.shift.shift.to_a
        assert_equal [1], list.shift.shift.shift.to_a
        assert_equal [], list.shift.shift.shift.shift.to_a
        assert_equal [], list.shift.shift.shift.shift.shift.to_a
      end

      describe "when the list is empty" do
        it "returns an empty list" do
          list = LinkedList.new
          assert_equal 0, list.shift.length
          assert_equal 0, list.shift.shift.length
        end
      end

      it "returns the same object" do
        list = LinkedList.new(1,2,3,4)
        assert_equal list.shift.object_id, list.shift.object_id
        assert_equal list.shift.shift.object_id, list.shift.shift.object_id
      end
    end

    describe "#unshift" do
      it "returns a new list with a new leading element" do
        list_1 = LinkedList.new({}, {}, [])
        list_2 = list_1.unshift(99)
        assert_equal [99, {}, {}, []], list_2.to_a
        assert_equal [{}, {}, []], list_1.to_a
      end

      describe "empty list" do
        it "makes it a one-item list" do
          list_1 = LinkedList.new
          list_2 = list_1.unshift("x")
          assert_equal [], list_1.to_a
          assert_equal ["x"], list_2.to_a
        end
      end
    end
  end

  describe "the end of the list" do
    describe "#last" do
      it "gives the last element" do
        list = LinkedList.new(12,34,56)
        assert_equal 56, list.last
      end

      describe "when the list is empty" do
        it "gives nil" do
          list = LinkedList.new
          assert_equal nil, list.last
        end
      end
    end

    describe "#push" do
      it "returns a new list with the item added" do
        list = LinkedList.new("a", nil, false)
        assert_equal ["a", nil, false, 0, 1], list.push(0).push(1).to_a
        assert_equal ["a", nil, false], list.to_a
      end

      describe "empty list" do
        it "makes a new one-item list" do
          list = LinkedList.new
          assert_equal [1], list.push(1).to_a
          assert_equal [], list.to_a
        end
      end
    end

    describe "#pop" do
      it "returns a new list without the last item" do
        list = LinkedList.new(nil, nil, nil)
        assert_equal [nil], list.pop.pop.to_a
        assert_equal [nil, nil, nil], list.to_a
      end

      describe "empty list" do
        it "returns an empty list" do
          list = LinkedList.new
          assert_equal [], list.pop.to_a
          assert_equal [], list.pop.pop.pop.to_a
        end
      end
    end
  end

  describe "index access" do
    describe "fetching values" do
      it "gets items by index" do
        list = LinkedList.new(1,2,3,4)
        assert_equal 4, list.get(3)
        assert_equal 4, list.push(5).get(3)
        assert_equal 5, list.push(5).get(4)
      end

      describe "when the index is larger than length" do
        it "returns nil" do
          list = LinkedList.new
          assert_equal nil, list.get(0)
          assert_equal nil, list.get(9)
          assert_equal nil, list.push(1).get(3)
        end
      end

      describe "when the index is negative" do
        it "fetches from the end of the list" do
          list = LinkedList.new(1,2,3,4)
          assert_equal 4, list.get(-1)
          assert_equal 2, list.get(-3)
        end
      end
    end

    describe "setting values" do
      it "returns a new list with a changed value" do
        list = LinkedList.new(1,2,3,4)
        list_2 = list.set(1, 4)
        assert_equal [1,2,3,4], list.to_a
        assert_equal [1,4,3,4], list_2.to_a

        list = LinkedList.new(1)
        assert_equal [2], list.set(0, 2).to_a
      end

      it "uses the same object for the unchanged part" do
        list_1 = LinkedList.new(nil, nil, nil, nil)
        list_2 = list_1.set(1, true)
        list_1_tail = list_1.shift.shift
        list_2_tail = list_2.shift.shift
        assert_equal [nil, nil], list_1_tail.to_a
        assert_equal [nil, nil], list_2_tail.to_a
        assert_equal list_1_tail.object_id, list_2_tail.object_id
      end

      describe "when the list is empty" do
        it "adds at that index" do
          list = LinkedList.new
          assert_equal [1], list.set(0, 1).to_a
        end
      end

      describe "when the index is greater than the length" do
        it "pads with nil" do
          list = LinkedList.new(1)
          list_2 = list.set(4, 2)
          assert_equal [1, nil, nil, nil, 2], list_2.to_a
        end

        it "even works with a zero-length list" do
          list = LinkedList.new
          list_2 = list.set(1, 2)
          list_3 = list_2.set(4, 2)
          assert_equal [nil, 2], list_2.to_a
          assert_equal [nil, 2, nil, nil, 2], list_3.to_a
        end
      end

      describe "when the index is negative" do
        it "works from the end of the list" do
          list = LinkedList.new(7,7,7)
          assert_equal [7,8,7], list.set(-2, 8).to_a
        end
      end
    end
  end

  describe "GC" do
    it "survives a GC run" do
      items = (1..100_000).to_a
      list_1 = LinkedList.new(*items)
      list_2 = list_1.shift
      list_3 = list_2.unshift(1)

      GC.start

      assert_equal 100_000, list_1.length
      assert_equal items, list_1.to_a

      assert_equal 99_999, list_2.length
      assert_equal items[1..-1], list_2.to_a

      assert_equal 100_000, list_3.length
      assert_equal items, list_3.to_a
    end
  end
end
