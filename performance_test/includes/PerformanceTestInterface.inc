<?php

/**
 * @file
 * Contains MedsReport interface.
 */

/**
 * The interface for export format.
 */
interface PerformanceTestInterface {

  /**
   * The callback function with used to export results to a file.
   */
  public function exportResults();

  /**
   * Each of test can specify a category where it will be appeared.
   */
  public function testCategory();
}
