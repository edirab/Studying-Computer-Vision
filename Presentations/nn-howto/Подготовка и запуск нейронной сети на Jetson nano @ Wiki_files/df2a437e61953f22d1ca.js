(window.webpackJsonp=window.webpackJsonp||[]).push([[11],{271:function(n,i){var e,t,a,h;e=window,t=e.innerWidth>e.innerHeight,a=e.innerWidth,h=$.throttle((function(){var n=e.innerWidth,i=e.innerHeight,h=n>i;h!==t&&n!==a&&($(e).trigger("orientchange",{landscape:h,width:n,height:i}),t=h,a=n)}),400),BEM.DOM.win.bind("resize",h),BEM.DOM.decl("i-ua",{onSetMod:{js:{inited:function(){this.bindToWin("orientchange",this._onOrientChange,this).__base.apply(this,arguments)}}},_onOrientChange:function(n,i){var e=this.__self,t=document.documentElement,a=t.className,h="i-ua_orient_"+(i.landscape?"landscape":"portrait");-1===a.indexOf(h)&&(t.className=a.replace(/\bi-ua_orient_\w+\b/,h)),e.width=i.width,e.height=i.height,e.landscape=i.landscape}},{width:e.innerWidth,height:e.innerHeight,landscape:t})}}]);
//# sourceMappingURL=df2a437e61953f22d1ca.js.map