<?php

namespace App;

class Listing {

  public function __construct($name, $description, $price) {
    /*
     * Must call 'htmlspecialchars' in order to ensure
     * no vulnerabilities within html that is constructed.
     */
    $this->name = htmlspecialchars($name);
    $this->description = htmlspecialchars($description);
    $this->price = htmlspecialchars($price);
  }

  public function toHTML() {
      return "<div class='listing'>".
             "  <h2>".$this->name."</h2>".
             "  <h3>".$this->price."</h3>".
             "  <p>".$this->description."</p>".
             "</div>";
  }

}

?>
