Pod::Spec.new do |s|
  s.name         = "Metawear-iOSAPI"
  s.version      = "2.5.1"
  s.summary      = "API for iOS + documentation files for the MetaWear platform"
  s.description  = <<-DESC
                   This library allows for simple interfacing with the MetaWear platform. 
                   You can control every part of the board through simple API calls to get
                   you're projects up and running fast.  See www.mbientlab.com for details.
                   DESC
  s.license      = { :type => 'Commercial', :text => 'See https://www.mbientlab.com/terms/', :file => 'LICENSE' }
  s.homepage     = "http://www.mbientlab.com"
  s.author       = { "Stephen" => "developers@mbientlab.com" }
  s.social_media_url   = "https://twitter.com/mbientLab"
  s.documentation_url  = "https://www.mbientlab.com/docs/metawear/ios/#{s.version}/index.html"
  s.platform     = :ios, "7.1"
  s.source       = { :git => "https://github.com/mbientlab/Metawear-iOSAPI.git", :tag => "#{s.version}" }
  s.vendored_frameworks = 'MetaWear.framework'
  s.source_files = "MetaWear.framework/**/*.h"
  s.requires_arc = true
  s.ios.frameworks      = 'CoreData', 'CoreBluetooth'
  s.dependency 'Bolts/Tasks', '~> 1.7'
  s.dependency 'FastCoding', '~> 3.2.1'
end
