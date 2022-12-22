
import frmWrk.website as website

def set_color ( color ):
    print( "Color not implemented yet!", color )

def set_mode ( mode ):
    print( "Mode not implemented yet!", mode )

def event_handler ( method, path ):
    if method != "GET": return
    print( path )
    if not "/?" in path: return
    if "?mode=" in path:
        set_mode( path.split( "?mode=" )[-1] )

    elif "?color=" in path:
        set_color( path.split( "?color=" )[-1] )

    print( method, path )

webServer = website.WebServer( "", 8080, './assets/', event_handler=event_handler )
webServer.start( )


