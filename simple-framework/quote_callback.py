def quoteCb( quote ):
    print 'Python Quote Callback!'
    print 'Last Trade Price: $', quote["lt"]
    print 'Bid: $', quote["bid"]
    print 'Ask: $', quote["ask"]

    print 'Resetting bid to $99.99'
    quote["bid"] = 99.99
    print 'Bid: $', quote["bid"]
    return
