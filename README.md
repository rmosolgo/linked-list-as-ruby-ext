# LinkedList

An immutable linked list for Ruby, implemented as a C extension.

### About

This list has a chain of `struct Node`s in C, each one _may_ have a Ruby `LinkedList` object as its owner.

```
       C Node           Ruby LinkedList
  ┌────────────────┐      ┌──────────┐
  │ value  (VALUE) │ <------ DATA    │
  │ owner  (VALUE) -----> │          │
  │ length (int)   │      └──────────┘   
  │ next   (Node*) │
  └───|────────────┘
      V
  ┌────────────────┐      
  │ value  (VALUE) │
  │ owner  (VALUE) │      (Some nodes
  │ length (int)   │       don't have
  │ next   (Node*) │       Ruby owners)
  └───|────────────┘
      V  
  ┌────────────────┐      ┌──────────┐
  │ value  (VALUE) │ <------ DATA    │
  │ owner  (VALUE) -----> │          │
  │ length (int)   │      └──────────┘   
  │ next   (Node*) │
  └────────────────┘
```

It's generally _slower_ than `Hamster::List` because `Hamster::List` has a lot of lazy implementations. But if you benchmark non-lazy operations, it's faster 😎

```
~/projects/linked_list $ ruby benchmark.rb
                   user     system      total        real
Hamster::List  5.750000   0.030000   5.780000 (  5.806201)
LinkedList     0.070000   0.010000   0.080000 (  0.071539)
~/projects/linked_list $ ruby benchmark.rb
                   user     system      total        real
Hamster::List  5.850000   0.050000   5.900000 (  5.927784)
LinkedList     0.070000   0.000000   0.070000 (  0.072522)
```

### API

- `.new(*items)`
- `#each(&block)` calls the block with each item
- `#first` gets the first item in the list
- `#last` gets the last item in the list
- `#unshift(item)` returns a new list with `item` at the first position
- `#shift` returns a new list _without_ the first item
- `#push(item)` returns a new list with `item` at the last position
- `#pop` returns a new list _without_ the last item
- `#get(index)` returns the item at that index (or `nil` if the index isn't present)
- `#set(index, item)` returns a new list with `item` at `index`, padding with `nil`s if the index is out of range

### Bugs

About 1 in 3 test runs crash during shutdown. It's gotta be something in GC, but I don't understand what it is ...  

```
# Running:

...../Users/rmosolgo/projects/linked_list/test/linked_list_test.rb:230: [BUG] Segmentation fault at 0x00000000000000
ruby 2.3.0p0 (2015-12-25 revision 53290) [x86_64-darwin14]

-- Crash Report log information --------------------------------------------
   See Crash Report log file under the one of following:
     * ~/Library/Logs/CrashReporter
     * /Library/Logs/CrashReporter
     * ~/Library/Logs/DiagnosticReports
     * /Library/Logs/DiagnosticReports
   for more details.
Don't forget to include the above Crash Report log file in bug reports.

-- Control frame information -----------------------------------------------
c:0024 p:---- s:0105 e:000104 CFUNC  :start
c:0023 p:0060 s:0102 e:000101 LAMBDA /Users/rmosolgo/projects/linked_list/test/linked_list_test.rb:230 [FINISH]
c:0022 p:0029 s:0096 e:000095 BLOCK  /Users/rmosolgo/.rbenv/versions/2.3.0/lib/ruby/gems/2.3.0/gems/minitest-5.8.4/lib/minitest/test.rb:108
c:0021 p:0006 s:0094 e:000093 METHOD /Users/rmosolgo/.rbenv/versions/2.3.0/lib/ruby/gems/2.3.0/gems/minitest-5.8.4/lib/minitest/test.rb:205
c:0020 p:0009 s:0090 e:000089 BLOCK  /Users/rmosolgo/.rbenv/versions/2.3.0/lib/ruby/gems/2.3.0/gems/minitest-5.8.4/lib/minitest/test.rb:105
c:0019 p:0020 s:0088 e:000087 METHOD /Users/rmosolgo/.rbenv/versions/2.3.0/lib/ruby/gems/2.3.0/gems/minitest-5.8.4/lib/minitest/test.rb:256
c:0018 p:0009 s:0084 e:000083 BLOCK  /Users/rmosolgo/.rbenv/versions/2.3.0/lib/ruby/gems/2.3.0/gems/minitest-5.8.4/lib/minitest/test.rb:104
c:0017 p:0037 s:0082 E:001830 METHOD /Users/rmosolgo/.rbenv/versions/2.3.0/lib/ruby/gems/2.3.0/gems/minitest-5.8.4/lib/minitest.rb:331
c:0016 p:0041 s:0075 E:001798 METHOD /Users/rmosolgo/.rbenv/versions/2.3.0/lib/ruby/gems/2.3.0/gems/minitest-5.8.4/lib/minitest/test.rb:276
c:0015 p:0009 s:0069 E:001710 METHOD /Users/rmosolgo/.rbenv/versions/2.3.0/lib/ruby/gems/2.3.0/gems/minitest-5.8.4/lib/minitest/test.rb:103
c:0014 p:0014 s:0066 e:000065 METHOD /Users/rmosolgo/.rbenv/versions/2.3.0/lib/ruby/gems/2.3.0/gems/minitest-5.8.4/lib/minitest.rb:778
c:0013 p:0020 s:0060 e:000058 METHOD /Users/rmosolgo/.rbenv/versions/2.3.0/lib/ruby/gems/2.3.0/gems/minitest-5.8.4/lib/minitest.rb:305
c:0012 p:0014 s:0053 e:000052 BLOCK  /Users/rmosolgo/.rbenv/versions/2.3.0/lib/ruby/gems/2.3.0/gems/minitest-5.8.4/lib/minitest.rb:293 [FINISH]
c:0011 p:---- s:0050 e:000049 CFUNC  :each
c:0010 p:0010 s:0047 e:000046 BLOCK  /Users/rmosolgo/.rbenv/versions/2.3.0/lib/ruby/gems/2.3.0/gems/minitest-5.8.4/lib/minitest.rb:292
c:0009 p:0037 s:0045 E:0015d0 METHOD /Users/rmosolgo/.rbenv/versions/2.3.0/lib/ruby/gems/2.3.0/gems/minitest-5.8.4/lib/minitest.rb:331
c:0008 p:0024 s:0038 E:001568 METHOD /Users/rmosolgo/.rbenv/versions/2.3.0/lib/ruby/gems/2.3.0/gems/minitest-5.8.4/lib/minitest.rb:318
c:0007 p:0085 s:0032 E:001510 METHOD /Users/rmosolgo/.rbenv/versions/2.3.0/lib/ruby/gems/2.3.0/gems/minitest-5.8.4/lib/minitest.rb:291
c:0006 p:0013 s:0025 e:000024 BLOCK  /Users/rmosolgo/.rbenv/versions/2.3.0/lib/ruby/gems/2.3.0/gems/minitest-5.8.4/lib/minitest.rb:152 [FINISH]
c:0005 p:---- s:0022 e:000021 CFUNC  :map
c:0004 p:0042 s:0019 e:000018 METHOD /Users/rmosolgo/.rbenv/versions/2.3.0/lib/ruby/gems/2.3.0/gems/minitest-5.8.4/lib/minitest.rb:152
c:0003 p:0158 s:0011 e:000010 METHOD /Users/rmosolgo/.rbenv/versions/2.3.0/lib/ruby/gems/2.3.0/gems/minitest-5.8.4/lib/minitest.rb:129
c:0002 p:0071 s:0005 E:000f48 BLOCK  /Users/rmosolgo/.rbenv/versions/2.3.0/lib/ruby/gems/2.3.0/gems/minitest-5.8.4/lib/minitest.rb:56 [FINISH]
c:0001 p:0000 s:0002 E:001210 (none) [FINISH]

-- Ruby level backtrace information ----------------------------------------
/Users/rmosolgo/.rbenv/versions/2.3.0/lib/ruby/gems/2.3.0/gems/minitest-5.8.4/lib/minitest.rb:56:in `block in autorun'
/Users/rmosolgo/.rbenv/versions/2.3.0/lib/ruby/gems/2.3.0/gems/minitest-5.8.4/lib/minitest.rb:129:in `run'
/Users/rmosolgo/.rbenv/versions/2.3.0/lib/ruby/gems/2.3.0/gems/minitest-5.8.4/lib/minitest.rb:152:in `__run'
/Users/rmosolgo/.rbenv/versions/2.3.0/lib/ruby/gems/2.3.0/gems/minitest-5.8.4/lib/minitest.rb:152:in `map'
/Users/rmosolgo/.rbenv/versions/2.3.0/lib/ruby/gems/2.3.0/gems/minitest-5.8.4/lib/minitest.rb:152:in `block in __run'
/Users/rmosolgo/.rbenv/versions/2.3.0/lib/ruby/gems/2.3.0/gems/minitest-5.8.4/lib/minitest.rb:291:in `run'
/Users/rmosolgo/.rbenv/versions/2.3.0/lib/ruby/gems/2.3.0/gems/minitest-5.8.4/lib/minitest.rb:318:in `with_info_handler'
/Users/rmosolgo/.rbenv/versions/2.3.0/lib/ruby/gems/2.3.0/gems/minitest-5.8.4/lib/minitest.rb:331:in `on_signal'
/Users/rmosolgo/.rbenv/versions/2.3.0/lib/ruby/gems/2.3.0/gems/minitest-5.8.4/lib/minitest.rb:292:in `block in run'
/Users/rmosolgo/.rbenv/versions/2.3.0/lib/ruby/gems/2.3.0/gems/minitest-5.8.4/lib/minitest.rb:292:in `each'
/Users/rmosolgo/.rbenv/versions/2.3.0/lib/ruby/gems/2.3.0/gems/minitest-5.8.4/lib/minitest.rb:293:in `block (2 levels) in run'
/Users/rmosolgo/.rbenv/versions/2.3.0/lib/ruby/gems/2.3.0/gems/minitest-5.8.4/lib/minitest.rb:305:in `run_one_method'
/Users/rmosolgo/.rbenv/versions/2.3.0/lib/ruby/gems/2.3.0/gems/minitest-5.8.4/lib/minitest.rb:778:in `run_one_method'
/Users/rmosolgo/.rbenv/versions/2.3.0/lib/ruby/gems/2.3.0/gems/minitest-5.8.4/lib/minitest/test.rb:103:in `run'
/Users/rmosolgo/.rbenv/versions/2.3.0/lib/ruby/gems/2.3.0/gems/minitest-5.8.4/lib/minitest/test.rb:276:in `with_info_handler'
/Users/rmosolgo/.rbenv/versions/2.3.0/lib/ruby/gems/2.3.0/gems/minitest-5.8.4/lib/minitest.rb:331:in `on_signal'
/Users/rmosolgo/.rbenv/versions/2.3.0/lib/ruby/gems/2.3.0/gems/minitest-5.8.4/lib/minitest/test.rb:104:in `block in run'
/Users/rmosolgo/.rbenv/versions/2.3.0/lib/ruby/gems/2.3.0/gems/minitest-5.8.4/lib/minitest/test.rb:256:in `time_it'
/Users/rmosolgo/.rbenv/versions/2.3.0/lib/ruby/gems/2.3.0/gems/minitest-5.8.4/lib/minitest/test.rb:105:in `block (2 levels) in run'
/Users/rmosolgo/.rbenv/versions/2.3.0/lib/ruby/gems/2.3.0/gems/minitest-5.8.4/lib/minitest/test.rb:205:in `capture_exceptions'
/Users/rmosolgo/.rbenv/versions/2.3.0/lib/ruby/gems/2.3.0/gems/minitest-5.8.4/lib/minitest/test.rb:108:in `block (3 levels) in run'
/Users/rmosolgo/projects/linked_list/test/linked_list_test.rb:230:in `block (3 levels) in <top (required)>'
/Users/rmosolgo/projects/linked_list/test/linked_list_test.rb:230:in `start'

-- Machine register context ------------------------------------------------
 rax: 0x00027f9764000000 rbx: 0x00027f9764003b80 rcx: 0x000000000000017c
 rdx: 0x0000000000000005 rdi: 0x00007f97624095a0 rsi: 0x00027f9764003b80
 rbp: 0x00007fff5be52160 rsp: 0x00007fff5be52150  r8: 0x000000000000001d
  r9: 0x00007f9764d00000 r10: 0x0000000000000020 r11: 0x00007f9764d00000
 r12: 0x00007f9762720640 r13: 0x00007f976300ee28 r14: 0x00007f97624095a0
 r15: 0x00007f976300c000 rip: 0x0000000103e17335 rfl: 0x0000000000010206

-- C level backtrace information -------------------------------------------
0   ruby                                0x0000000103f494d4 rb_vm_bugreport + 388
1   ruby                                0x0000000103debdc3 rb_bug_context + 483
2   ruby                                0x0000000103ebe553 sigsegv + 83
3   libsystem_platform.dylib            0x00007fff87ae1f1a _sigtramp + 26
4   ruby                                0x0000000103e17335 rgengc_check_relation + 69
5   ???                                 0x00007f97624095a0 0x0 + 140288165189024
```
