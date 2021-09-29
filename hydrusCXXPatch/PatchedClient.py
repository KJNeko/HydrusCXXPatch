#should match the client.py in hydrus with override changes

from hydrus.core import HydrusConstants as HC
from hydrus.core import HydrusData
from hydrus.core import HydrusExceptions
from hydrus.core import HydrusSerialisable
from hydrus.core import HydrusVideoHandling
from hydrus.core import HydrusFileHandling
from hydrus import hydrus_client

#override section

from ctypes import * 

from sys import platform
#windows vs linux check

if platform == "linux" or platform == "linux2":
    c_lib_numpy = CDLL("libHydrusPatch.so")
elif platform == "win32":
    c_lib_numpy = CDLL("libHydrusPatch.dll")


#if platform == "linux" or platform == "linux2":
#    c_lib_numpy = npct.load_library("hydrus/lib/libHydrusPatch.so", ".")
#elif platform == "win32":
#    c_lib_numpy = npct.load_library("hydrus/lib/libHydrusPatch.dll", ".")
#c_lib_numpy.getMimeCXX.restype = ctypes.c_int
#c_lib_numpy.getMimeCXX.argtypes = [ctypes.c_char_p]


def GetMimeCXX( path, ok_to_look_for_hydrus_updates = False ):
    
    mime = c_lib_numpy.getMimeCXX( c_char_p(path.encode('utf-8')) )

    if mime != HC.APPLICATION_UNKNOWN:
        if mime == HC.UNDETERMINED_WM:
            
            if HydrusVideoHandling.HasVideoStream( path ):
                
                return HC.VIDEO_WMV
                
            
            # we'll catch and verify wma later            
        else:
            return mime

    print("We didn't find it on our end", mime)

    #This check seems useless? How do we ever get here? -KJ
    try:
        
        mime = HydrusVideoHandling.GetMime( path )
        
        if mime != HC.APPLICATION_UNKNOWN:
            
            return mime
            
        
    except HydrusExceptions.UnsupportedFileException:
        
        pass
        
    except Exception as e:
        
        HydrusData.Print( 'FFMPEG had trouble with: ' + path )
        HydrusData.PrintException( e, do_wait = False )
        
    
    if ok_to_look_for_hydrus_updates:
        
        with open( path, 'rb' ) as f:
            
            update_network_bytes = f.read()
            
        
        try:
            
            update = HydrusSerialisable.CreateFromNetworkBytes( update_network_bytes )
            
            if isinstance( update, HydrusNetwork.ContentUpdate ):
                
                return HC.APPLICATION_HYDRUS_UPDATE_CONTENT
                
            elif isinstance( update, HydrusNetwork.DefinitionsUpdate ):
                
                return HC.APPLICATION_HYDRUS_UPDATE_DEFINITIONS
                
            
        except:
            
            pass

HydrusFileHandling.GetMime = GetMimeCXX

print("Applied Patches")
#override end


if __name__ == '__main__':
    
    hydrus_client.boot()
    
