# norootforbuild

Name:		easypaint
Version:	0.1.0
Release:	0
License:	MIT
Vendor:		Nikita Grishko <grin.minsk@gmail.com>
Source:		EasyPaint-%{version}.tar.bz2
Group:		Graphics
Summary:	Easy graphic editing program
BuildRequires:	gcc-c++, cmake, pkgconfig(QtGui)
%if 0%{?suse_version}
BuildRequires: update-desktop-files
%endif  
BuildRoot:	%{_tmppath}/%{name}-%{version}-build 

%description
%{summary}

%prep
%setup -q -n EasyPaint-%{version}

%build
mkdir build
pushd build
cmake .. -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_BUILD_TYPE=release
make
popd

%install
%{__rm} -rf %{buildroot}
pushd build
make DESTDIR=%{buildroot} install
popd
%if 0%{?suse_version}
	%suse_update_desktop_file %{name}  
%endif

%clean
%{__rm} -rf %{buildroot}

%files
%defattr(-,root,root,-)
%{_bindir}/%{name}
%{_datadir}/%{name}/
%{_datadir}/applications/%{name}.desktop
%{_datadir}/pixmaps/%{name}_64.png

%changelog
* Thu Apr 10 2012 Gr1N <grin.minsk@gmail.com>
- 0.1.0, first release
* Fri Apr 15 2011 TI_Eugene <ti.eugene@gmail.com>
- 0.0.1, initial OBS release
