import { ComponentFixture, TestBed } from '@angular/core/testing';

import { GaugeConsumoComponent } from './gauge-consumo.component';

describe('GaugeConsumoComponent', () => {
  let component: GaugeConsumoComponent;
  let fixture: ComponentFixture<GaugeConsumoComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      imports: [GaugeConsumoComponent]
    })
    .compileComponents();

    fixture = TestBed.createComponent(GaugeConsumoComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
