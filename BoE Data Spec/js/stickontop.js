window.onscroll = function() {AdjustDescriptionPanelYPos()};

var DescriptionPanel = document.getElementById("nav-tabContent");
var sticky = DescriptionPanel.offsetTop;

// Add the sticky class to the header when you reach its scroll position. Remove "sticky" when you leave the scroll position
function AdjustDescriptionPanelYPos() {
  if (window.pageYOffset > sticky - 56) {
    DescriptionPanel.classList.add("staytop");
  } else {
    DescriptionPanel.classList.remove("staytop");
  }
} 