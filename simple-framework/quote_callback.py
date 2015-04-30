# quoteCb form options:
#
# 1) def quoteCb( quote, data, output ):
#
# 2) def quoteCb( quote, data ):
#     return output
#
# #2 has the downside that they have to construct the object themselves
# #1 has the downside that it uses a sink argument, but probably better

# REVISIT (plesslie); is there a way to make the quote dict immutable to the
# end user? that way I could re-use my dict.  Maybe just keep the dict object
# around that all quotes will use and dump whatever values the user sets each time.

def quoteCb( quote ):
    print 'Python Quote Callback!'
    print 'Last Trade Price: $', quote["lt"]
    print 'Bid: $', quote["bid"]
    print 'Ask: $', quote["ask"]


    return
