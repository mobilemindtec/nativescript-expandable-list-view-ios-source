Pod::Spec.new do |s|
  s.name         = "NSExpandableTableView"
  s.version      = "0.0.1"
  s.summary      = "NativeScript expandable list ios sources."
  s.description  = "NativeScript expandable list ios sources."
  s.homepage     = "
git@github.com:mobilemindtec/nativescript-expandable-list-view-ios-source.git

"
  s.license      = { :type => 'MIT', :file => 'LICENSE' }
  s.author       = { "orta" => 'ricardo@mobilemind.com.br' }
  s.source       = { :git => "
git@github.com:mobilemindtec/nativescript-expandable-list-view-ios-source.git

", :tag => s.version.to_s }
  s.platform     = :ios, '8.0'
  s.source_files = 'NSExpandableTableView.{h,m}'
  s.resources = '*.{png}'  
  s.requires_arc = true

end
